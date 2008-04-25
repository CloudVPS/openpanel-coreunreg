#ifndef _coreunreg_H
#define _coreunreg_H 1
#include <grace/application.h>

//  -------------------------------------------------------------------------
/// Main application class.
//  -------------------------------------------------------------------------
class coreunregApp : public application
{
public:
		 	 coreunregApp (void) :
				application ("com.openpanel.tools.coreunreg")
			 {
			 }
			~coreunregApp (void)
			 {
			 }

	int		 main (void);
};

#endif
