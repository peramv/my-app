#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_object_not_initialized : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_object_not_initialized() { }
		~CIFast_IFast_ifastcbo_err_object_not_initialized() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_OBJECT_NOT_INITIALIZED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Account allocations must differ in account number.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Account allocations must differ in account number.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Konto-Zuweisungen müssen sich in der Kontonummer unterscheiden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Las asignaciones de cuentas deben diferir en número de cuenta.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Il y a un problème interne.  L'objet n'est pas initialisé.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er is een intern probleem.  Object is niet geïnitialiseerd")); }

        // Actions
		virtual DString GetAction_FR_CA() const { return DString(I_("Vérifiez que l'objet est initialisé.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Controleer of het object is geïnitialiseerd")); }
	};
}



