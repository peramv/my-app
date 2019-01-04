#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_corr_bank_fields_shoud_be_entered : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_corr_bank_fields_shoud_be_entered() { }
		~CIFast_IFast_ifastcbo_err_corr_bank_fields_shoud_be_entered() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_CORR_BANK_FIELDS_SHOUD_BE_ENTERED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Correspondent bank information should be entered for international wire.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Entsprechende Bankinformation für Auslandsübermittlung sollte eingegeben sein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Debe introducirse la información bancaria correspondiente para transferencia cablegráfica internacional.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'information bancaire correspondante devrait être saisie pour une opération électronique internationale.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Bankgegevens correspondent moeten ingevuld zijn voor internationale telegrafische order")); }

        // Actions
	};
}



