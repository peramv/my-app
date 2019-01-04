#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_fifo_not_exist : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_fifo_not_exist() { }
		~CIFast_IFast_ifastdbrkr_err_fifo_not_exist() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FIFO_NOT_EXIST")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("FIFO units do not exist.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("FIFO-Anteile existieren NICHT.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Las unidades FIFO NO existen")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Unités PEPS inexistantes")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er bestaan GEEN FIFO-eenheden")); }

        // Actions
	};
}



