#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_purc_resp_not_supported : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_purc_resp_not_supported() { }
		~CIFast_IFast_ifastcbo_warn_purc_resp_not_supported() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_PURC_RESP_NOT_SUPPORTED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("This RESP system does not support eCSEG, CLB, ACES.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("This RESP system does not support eCSEG, CLB, ACES.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Ce système REEE ne supporte pas les SCEE, BEC et ACES.")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Please verify that the RESP transaction does not contain any of these components.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Please verify that the RESP transaction does not contain any of these components.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Veuillez vérifier que la transaction REEE ne contient aucun de ces éléments.")); }
	};
}



