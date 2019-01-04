#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Infrastructure_bpbase_bp_err_item_not_valid : public CConditionObject
	{
	public:
		CBase_Infrastructure_bpbase_bp_err_item_not_valid() { }
		~CBase_Infrastructure_bpbase_bp_err_item_not_valid() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("BP_ERR_ITEM_NOT_VALID")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("bpbase")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The system does not recognize this financial institution branch.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("The system does not recognize this financial institution branch.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Das System erkennt diese Finanzinstitut-Filiale nicht.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El sistema no reconoce esta sucursal de institución financiera.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le système ne reconnaît pas cette unité de service de l'institution financière.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Het systeem herkent het filiaal van deze financiële instelling niet")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Verify financial institution branch and re-enter.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Verify financial institution branch and re-enter.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Überprüfen Sie die Finanzinstitut-Filiale und geben Sie sie erneut ein.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Verifique la sucursal de institución financiera y vuelva a introducirla.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Vérifiez l'unité de service de l'institution financière et réessayez.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Controleer het filiaal van de financiële instelling voer het opnieuw in")); }
	};
}



