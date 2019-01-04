#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_broker_not_eligible : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_broker_not_eligible() { }
		~CIFast_IFast_ifastdbrkr_err_broker_not_eligible() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_BROKER_NOT_ELIGIBLE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Broker/Branch/Sales Representative is not Trail Eligible.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Broker/Branch/Sales Representative is not Trail Eligible.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Broker/Filiale/Verkaufsvertreter ist nicht Trailerprovisions-geeignet.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El corredor/sucursal/representante de ventas no son aptos para comisión por servicio")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le courtier/l'unité de service/le représentant des ventes n'est pas admissible à l'administration.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Makelaar/filiaal/vertegenwoordiger komt niet in aanmerking voor verkoopbonus")); }

        // Actions
	};
}



