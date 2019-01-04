#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_warn_fund_class_sysgentrfout_stop_flag_on : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_warn_fund_class_sysgentrfout_stop_flag_on() { }
		~CIFast_IFast_ifastcbo_err_warn_fund_class_sysgentrfout_stop_flag_on() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_WARN_FUND_CLASS_SYSGENTRFOUT_STOP_FLAG_ON")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Fund %FUND% and Class %CLASS% has System Generated Transfer Out stop flag turned on.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Fund %FUND% and Class %CLASS% has System Generated Transfer Out stop flag turned on.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Fund %FUND% and Class %CLASS% has System Generated Transfer Out stop flag turned on.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le signal d'arrêt de transfert sortant généré par le système du fonds %FUND% et de la classe %CLASS% est activé.")); }

        // Actions
	};
}



