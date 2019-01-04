#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_dicore_err_kyc_data_not_found : public CConditionObject
	{
	public:
		CIFast_Infrastructure_dicore_err_kyc_data_not_found() { }
		~CIFast_Infrastructure_dicore_err_kyc_data_not_found() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_KYC_DATA_NOT_FOUND")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("dicore")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("KYC data not found")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("KYC data not found")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("KYC data not found")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Données du profil d'investisseur introuvables")); }

        // Actions
	};
}



