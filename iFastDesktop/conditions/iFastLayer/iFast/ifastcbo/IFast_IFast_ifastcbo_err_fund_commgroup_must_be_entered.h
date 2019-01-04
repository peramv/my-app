#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_fund_commgroup_must_be_entered : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_fund_commgroup_must_be_entered() { }
		~CIFast_IFast_ifastcbo_err_fund_commgroup_must_be_entered() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FUND_COMMGROUP_MUST_BE_ENTERED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Either Fund/Class or Commission Group must be specified.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Entweder Fonds/Klasse oder CommGroup muss spezifiziert werden")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Debe especificarse el fondo/clase o el grupo de comunicaciones.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le fonds/la classe ou le groupe de commission doivent être spécifiés.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Fonds/categorie of Commissiegroep moet worden opgegeven")); }

        // Actions
	};
}



