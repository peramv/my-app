#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_salesperson_is_not_permitted : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_salesperson_is_not_permitted() { }
		~CIFast_IFast_ifastcbo_err_salesperson_is_not_permitted() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_SALESPERSON_IS_NOT_PERMITTED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Salesperson is not permitted new business activity.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Salesperson is not permitted new business activity.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Verkaufsvertreter ist nicht für eine neue Geschäftstätigkeit zugelassen.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se permite a este vendedor nueva actividad comercial")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le représentant des ventes n'est pas autorisé à faire de nouvelles affaires.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Vertegenwoordiger mag geen nieuwe bedrijfsactiviteit aangaan")); }

        // Actions
	};
}



