#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_vmreadresponse_error : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_vmreadresponse_error() { }
		~CIFast_IFast_dita2kdb_dita2kdb_vmreadresponse_error() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_VMREADRESPONSE_ERROR")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("There is an internal problem.  Copy object not initialized.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("There is an internal problem.  Copy object not initialized.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Es gibt ein internes Problem.  Kopierobjekt nicht initialisiert.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Hay un problema interno.  El objeto de copia no se inicializó.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Il y a un problème interne. La copie de l'objet n'est pas initialisée.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er is een intern probleem.  Kopieerobject is niet geïnitialiseerd")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Perform initialization of object.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Perform initialization of object.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Führen Sie die Initialisierung des Objekts durch.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Perform initialization of object.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Procédez à l'initialisation de l'objet.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Voer de initialisatie van het object uit")); }
	};
}



