#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_rif_invalid_rif_src_of_fund : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_rif_invalid_rif_src_of_fund() { }
		~CIFast_IFast_ifastcbo_err_rif_invalid_rif_src_of_fund() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_RIF_INVALID_RIF_SRC_OF_FUND")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Only 'I' and 'E' is valid.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Only 'I' and 'E' is valid.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Nur \"I\" und \"E\" sind gültig.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Sólo 'I' y 'E' son opciones válidas.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Seuls I et E sont valides.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Alleen 'I' en 'E' zijn geldig")); }

        // Actions
	};
}



