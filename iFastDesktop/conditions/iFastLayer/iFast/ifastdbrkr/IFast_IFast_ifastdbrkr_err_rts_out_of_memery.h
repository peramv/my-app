#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_rts_out_of_memery : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_rts_out_of_memery() { }
		~CIFast_IFast_ifastdbrkr_err_rts_out_of_memery() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_RTS_OUT_OF_MEMERY")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The iFast environment is out of memory. Please contact the service desk.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'environnement iFAST n'a plus de mémoire disponible. Veuillez communiquer avec le centre de services.")); }

        // Actions
	};
}



