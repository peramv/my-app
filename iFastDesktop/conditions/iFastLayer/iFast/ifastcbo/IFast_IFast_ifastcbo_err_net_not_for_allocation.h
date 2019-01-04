#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_net_not_for_allocation : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_net_not_for_allocation() { }
		~CIFast_IFast_ifastcbo_err_net_not_for_allocation() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NET_NOT_FOR_ALLOCATION")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Net is not allowed for Allocation trade.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Net is not allowed for Allocation trade.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Netto ist für Zuweisungshandel nicht erlaubt.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se permite Neto para una operación de asignación")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Net non autorisé pour une transaction de répartition")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Netto is niet toegestaan voor een allocatietransactie")); }

        // Actions
	};
}



