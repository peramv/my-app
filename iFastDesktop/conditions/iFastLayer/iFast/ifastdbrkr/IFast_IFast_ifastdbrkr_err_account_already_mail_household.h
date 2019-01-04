#pragma once

#include "..\..\..\ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_account_already_mail_household : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_account_already_mail_household() { }
		~CIFast_IFast_ifastdbrkr_err_account_already_mail_household() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ACCOUNT_ALREADY_IN_MAIL_HOUSEHOLD")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Copy fail: account is already in a mail household.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Copy fail: account is already in a mail household.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Copy fail: account is already in a mail household.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Copy fail: account is already in a mail household.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Échec : les comptes sont déjà associés à une adresse.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Copy fail: account is already in a mail household.")); }

		// Actions
	};
}



