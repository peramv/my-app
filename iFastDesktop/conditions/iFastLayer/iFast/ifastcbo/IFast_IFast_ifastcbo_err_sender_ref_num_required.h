#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_sender_ref_num_required : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_sender_ref_num_required() { }
		~CIFast_IFast_ifastcbo_err_sender_ref_num_required() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_SENDER_REF_NUM_REQUIRED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Sender reference number is required.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Sender reference number is required.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le numéro de référence de l'expéditeur est requis.")); }

        // Actions
	};
}



