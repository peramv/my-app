#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_delete_fundsponsor_fee_model : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_delete_fundsponsor_fee_model() { }
		~CIFast_IFast_ifastcbo_err_delete_fundsponsor_fee_model() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_DELETE_FUNDSPONSOR_FEE_MODEL")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("FundSponsor Fee Model can not be deleted because process date is different from current business date.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("FundSponsor Fee Model can not be deleted because process date is different from current business date.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le modèle de frais du promoteur de fonds ne peut être supprimé parce que la date de traitement est différente de la date opérationnelle actuelle.")); }

        // Actions
	};
}



