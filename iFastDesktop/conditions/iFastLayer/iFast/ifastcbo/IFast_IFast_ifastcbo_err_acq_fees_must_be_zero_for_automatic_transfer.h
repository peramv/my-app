#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_acq_fees_must_be_zero_for_automatic_transfer : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_acq_fees_must_be_zero_for_automatic_transfer() { }
		~CIFast_IFast_ifastcbo_err_acq_fees_must_be_zero_for_automatic_transfer() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ACQ_FEES_MUST_BE_ZERO_FOR_AUTOMATIC_TRANSFER")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Acquisition Fees must be 0 for Automatic Transfer.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Acquisition Fees must be 0 for Automatic Transfer.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Acquisition Fees must be 0 for Automatic Transfer.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les frais d'acquisition doivent être à zéro pour un transfert automatique.")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Please change the Acquisition Fee to 0 for an Automatic Transfer.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Please change the Acquisition Fee to 0 for an Automatic Transfer.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Please change the Acquisition Fee to 0 for an Automatic Transfer.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Pour un transfert automatique, veuillez régler les frais d'acquisition à zéro.")); }
	};
}



