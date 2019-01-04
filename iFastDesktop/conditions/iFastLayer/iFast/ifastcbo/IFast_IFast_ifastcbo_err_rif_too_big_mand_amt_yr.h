#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_rif_too_big_mand_amt_yr : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_rif_too_big_mand_amt_yr() { }
		~CIFast_IFast_ifastcbo_err_rif_too_big_mand_amt_yr() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_RIF_TOO_BIG_MAND_AMT_YR")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Mandatory Annual Amount must be smaller than Maximum.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Mandatory Annual Amount must be smaller than Maximum.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Obligatorischer Jahresbetrag muss kleiner als das Maximum sein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El monto anual obligatorio debe ser inferior al máximo.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le montant annuel requis doit être inférieur au maximum.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Verplicht jaarbedrag moet kleiner zijn dan maximum")); }

        // Actions
	};
}



