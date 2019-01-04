#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_acct_split_comm_no_active_date_range : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_acct_split_comm_no_active_date_range() { }
		~CIFast_IFast_ifastcbo_err_acct_split_comm_no_active_date_range() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ACCT_SPLIT_COMM_NO_ACTIVE_DATE_RANGE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("No active date range.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Kein aktiver Datumsbereich.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No hay un rango de fechas activo.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Plage de date inactive")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Geen actief datumbereik")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Please setup a new date range.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Please setup a new date range.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Please setup a new date range.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Veuillez régler une nouvelle plage de dates.")); }
	};
}



