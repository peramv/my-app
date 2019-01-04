#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_shareholder_below_69 : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_shareholder_below_69() { }
		~CIFast_IFast_ifastcbo_err_shareholder_below_69() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_SHAREHOLDER_BELOW_69")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("This shareholder is less than 69 years old.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("This shareholder is less than 69 years old.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Dieser Aktionär ist jünger als 69.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Este accionista tiene menos de 69 años.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Cet actionnaire a moins de 69 ans.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Deze aandeelhouder is jonger dan 69 jaar")); }

        // Actions
	};
}



