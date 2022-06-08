#include <stdio.h>
#include <nss.h>
#include <pk11pub.h>

/* It's possible to run without including secmodti.h but then
 * gdb won't be able to understand the PK11SlotInfo struct and
 * print *slot
 * will just output <incomplete type>
 * I copied secmodti.h and the files it includes to this directory.
 * */
#include "secmodti.h"

/* slot is initialized by init_profile() and freed by cleanup() */
static PK11SlotInfo *slot = NULL;

/* Inits the global struct slot */
int init_profile(char *profile_path)
{
	SECStatus error = NSS_Init(profile_path);

	if (error) {
		printf("Error initializing profile %s\n", profile_path);
		return 1;
	}

	slot = PK11_GetInternalKeySlot();
	if (!slot) {
		printf("Error getting internal slot\n");
		return 1;
	}

	if (!PK11_NeedLogin(slot)) {
		printf("Database is not password protected\n");
		return 1;
	}

	return 0;
}

/* Free slot and shut down libnss */
void cleanup(void)
{
	if (slot) {
		PK11_FreeSlot(slot);
		slot = NULL;
	}
	NSS_Shutdown();
}

int main(void)
{
	/* Change this path to your profile, may need sql: in front of the path
	 * but it seems to work without sql: too. Probably the default. */
	char *profile = "sql:/home/albert/.mozilla/firefox/myijelm2.default-esr";
	char *password = "iloveyou";
	int status;

	if (init_profile(profile)) {
		cleanup();
		return 1;
	}

#ifdef _SECMODTI_H_
	printf(	"\nInside gdb, run:\n"
		"  print *slot\n"
		"here if you included secmodti.h\n\n");
#endif

	/* Could guess passwords in a loop here */
	status = PK11_CheckUserPassword(slot, password);
	/* status 0 = correct password, status -2 = wrong password */
	printf("password status = %d\n", status);

	cleanup();

	return 0;
}

