#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_rif_wrong_value_mand_amt_yr : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_rif_wrong_value_mand_amt_yr() { }
		~CIFast_IFast_ifastcbo_err_rif_wrong_value_mand_amt_yr() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_RIF_WRONG_VALUE_MAND_AMT_YR")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Mandatory Annual Amount should be 0 or %MAND_AMT_YR_SYS_CALC%.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Mandatory Annual Amount should be 0 or %MAND_AMT_YR_SYS_CALC%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Obligatorischer jährlicher Betrag sollte 0 oder %MAND_AMT_YR_SYS_CALC% sein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El monto anual obligatorio debe ser 0 o %MAND_AMT_YR_SYS_CALC%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le montant annuel requis devrait être 0 ou %MAND_AMT_YR_SYS_CALC%.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Verplicht jaarbedrag moet 0 zijn of %MAND_AMT_YR_SYS_CALC%")); }

        // Actions
	};
}



