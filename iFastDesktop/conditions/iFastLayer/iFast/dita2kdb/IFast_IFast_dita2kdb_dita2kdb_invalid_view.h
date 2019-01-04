#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_invalid_view : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_invalid_view() { }
		~CIFast_IFast_dita2kdb_dita2kdb_invalid_view() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_INVALID_VIEW")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("There is an internal problem.  Object is not initialized.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("There is an internal problem.  Object is not initialized.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Es gibt ein internes Problem.  Das Objekt ist nicht initialisiert..")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Hay un problema interno.  El objeto no se inicializó.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Il y a un problème interne.  L'objet n'est pas initialisé.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er is een intern probleem.  Object is niet geïnitialiseerd")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Verify that object is initialized.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Verify that object is initialized.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Überprüfen Sie, ob das Objekt initialisiert wurde.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Verify that object is initialized.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Vérifiez que l'objet est initialisé.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Controleer of het object is geïnitialiseerd")); }
	};
}



