#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_rts_out_of_disk_space : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_rts_out_of_disk_space() { }
		~CIFast_IFast_ifastdbrkr_err_rts_out_of_disk_space() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_RTS_OUT_OF_DISK_SPACE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The system is out of disk space. Please contact the service desk.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le système n'a plus d'espace disque disponible. Veuillez communiquer avec le centre de services.")); }

        // Actions
	};
}



