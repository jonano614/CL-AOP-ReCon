//диалог офицера/компаньона
#include "DIALOGS\Officer_Common.c"

void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, Diag;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(Diag, NPChar.Dialog);

	ProcessBaseOfficerEvent(NPChar, link, Diag);
}
