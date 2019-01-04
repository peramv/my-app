#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_cancel_batch_must_be_prefixed_sp_dc : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_cancel_batch_must_be_prefixed_sp_dc() { }
		~CIFast_IFast_ifastcbo_err_cancel_batch_must_be_prefixed_sp_dc() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_CANCEL_BATCH_MUST_BE_PREFIXED_SP_DC")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("To cancel trade that settle batch has prefix SP or DC. The cancel batch must be prefixed same as settle batch.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Pour l'annulation de la transaction dont le préfixe du lot de rêglement est SP ou DC. Le lot d'annulation doit avoir le même préfixe que le lot de règlement.")); }

        // Actions
	};
}



