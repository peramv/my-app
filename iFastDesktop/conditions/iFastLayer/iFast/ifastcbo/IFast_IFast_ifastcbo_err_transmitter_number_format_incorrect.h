#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_transmitter_number_format_incorrect : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_transmitter_number_format_incorrect() { }
		~CIFast_IFast_ifastcbo_err_transmitter_number_format_incorrect() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_TRANSMITTER_NUMBER_FORMAT_INCORRECT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Transmitter Number format incorrect.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Transmitter Number format incorrect.")); }

        // Actions
	};
}