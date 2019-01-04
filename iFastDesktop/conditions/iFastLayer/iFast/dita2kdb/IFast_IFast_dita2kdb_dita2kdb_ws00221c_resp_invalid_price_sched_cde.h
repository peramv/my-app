﻿#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_price_sched_cde : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_price_sched_cde() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_price_sched_cde() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_INVALID_PRICE_SCHED_CDE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Federal Rate + Provincial Rate must be smaller than 100.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Federal Rate + Provincial Rate must be smaller than 100.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Bundessatz + Provinzsatz müssen kleiner als 100 sein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La tasa federal + la tasa provincial debe ser inferior a 100.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le taux fédéral additionné au taux provincial doit être inférieur à 100.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Federaal tarief + Provincietarief moet kleiner zijn dan 100")); }

        // Actions
	};
}



