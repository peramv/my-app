#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_ams_err_exchange_not_allowed : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_ams_err_exchange_not_allowed() { }
		~CIFast_IFast_ifastcbo_ams_err_exchange_not_allowed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("AMS_ERR_EXCHANGE_NOT_ALLOWED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("User does not have permission to perform exchanges on AMS Account.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("User does not have permission to perform exchanges on AMS Account.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("User does not have permission to perform exchanges on AMS Account.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'utilisateur n'est pas autorisé à effectuer des échanges dans le compte de service de gestion de portefeuille.")); }

        // Actions
	};
}



