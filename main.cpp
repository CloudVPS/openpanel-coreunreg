#include "coreunreg.h"

#include <querido/engine.h>
#include <grace/xmlschema.h>

APPOBJECT(coreunregApp);

//  =========================================================================
/// Main method.
//  =========================================================================
int coreunregApp::main (void)
{
	if (argv["*"].count() == 0)
	{
		ferr.printf ("%% Usage: coreunreg <Modulename>\n");
		return 1;
	}
	statstring modname = argv["*"][0];
	xmlschema modschema ("/var/openpanel/bin/openpaneld.app/Contents/Schemas/"
						 "com.openpanel.opencore.module.schema.xml");

	value dbinfo;
	dbinfo["path"] = "/var/openpanel/db/panel/panel.db";
	
	dbengine DB (dbengine::SQLite);
	if (! DB.open (dbinfo))
	{
		ferr.printf ("Could not open panel.db\n");
		return 1;
	}
	
	value modcache;
	modcache.loadshox ("/var/openpanel/cache/module.cache");
	if (modcache["modules"].exists (modname))
	{
		fout.printf ("%% Removing module from module.cache\n");
		modcache["modules"].rmval (modname);
	}
	modcache.saveshox ("/var/openpanel/cache/module.cache");
	
	string modxmlpath;
	modxmlpath.printf ("/var/openpanel/modules/%s/module.xml", modname.str());
	
	value modxml;
	modxml.loadxml (modxmlpath, modschema);
	foreach (cl, modxml["classes"])
	{
		value res;
		int classid;
		string qry;
		qry.printf ("SELECT id FROM objects WHERE class=1 AND metaid='%s'",
					cl.id().cval());
		if (DB.query (qry, res) && res.count())
		{
			fout.printf ("%% Nuking class %s\n", cl.id().cval());
			classid = res[0]["id"];
			qry.crop ();
			qry.printf ("DELETE FROM objects WHERE id=%i OR class=%i",
						classid, classid);
			DB.query (qry);
		}
	}
	
	return 0;
}

