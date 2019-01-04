#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_stop_date_backward : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_stop_date_backward() { }
		~CIFast_IFast_ifastcbo_err_stop_date_backward() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_STOP_DATE_BACKWARD")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Stop Date  can not be changed backward for existing record.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Stop Date  can not be changed backward for existing record.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La date d'arrêt ne peut être changée pour une date précédente pour l'enregistrement existant.")); }

        // Actions
	};
}



