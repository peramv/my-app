#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_interm_is_not_permit_wire : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_interm_is_not_permit_wire() { }
		~CIFast_IFast_ifastdbrkr_err_interm_is_not_permit_wire() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INTERM_IS_NOT_PERMIT_WIRE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Intermediary is not permitted to enter wire orders.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Mittler kann keine telegrafischen Bestellungen eingeben")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se permite al intermediario introducir órdenes de transferencias cablegráficas")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'intermédiaire n'est pas autorisé à entrer des ordres électroniques.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Tussenpersoon mag geen telegrafische orders invoeren")); }

        // Actions
	};
}



