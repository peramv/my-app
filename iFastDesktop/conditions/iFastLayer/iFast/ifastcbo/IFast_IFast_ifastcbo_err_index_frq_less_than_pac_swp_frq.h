#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_index_frq_less_than_pac_swp_frq : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_index_frq_less_than_pac_swp_frq() { }
		~CIFast_IFast_ifastcbo_err_index_frq_less_than_pac_swp_frq() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INDEX_FRQ_LESS_THAN_PAC_SWP_FRQ")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Index frequency must be greater than or equal to the PAC/Savings Plan frequency.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Index-Häufigkeit muss größer oder gleich der Häufigkeit des PAC/Spar-Plans sein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La frecuencia de índice debe ser superior o igual a la frecuencia del PAC/plan de ahorro.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La fréquence d'indexation doit être supérieure ou égale à la fréquence du PAC/régime d'épargne.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Indexfrequentie moet groter zijn dan of gelijk aan de frequentie van het VGC/Savings Plan")); }

        // Actions
	};
}



