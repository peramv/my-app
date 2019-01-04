#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_ifastcbo_err_identical_acct_default_allocs : public CConditionObject
	{
	public:
		CIFast_Infrastructure_ifastcbo_err_identical_acct_default_allocs() { }
		~CIFast_Infrastructure_ifastcbo_err_identical_acct_default_allocs() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_IDENTICAL_ACCT_DEFAULT_ALLOCS")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Object is not initialized.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Object is not initialized.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Das Objekt ist nicht initialisiert.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El objeto no se inicializó.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'objet n'a pas été initialisé.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Object is niet geïnitialiseerd")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Verify that object is initialized.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Verify that object is initialized.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Überprüfen Sie, ob das Objekt initialisiert wurde.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Verify that object is initialized.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Vérifiez que l'objet est initialisé.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Controleer of het object is geïnitialiseerd")); }
	};
}



