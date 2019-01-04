#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_comm_shares_rec_error : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_comm_shares_rec_error() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_comm_shares_rec_error() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_COMM_SHARES_REC_ERROR")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Mandatory Annual Amount must be smaller than Maximum.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Mandatory Annual Amount must be smaller than Maximum.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Obligatorischer Jahresbetrag muss kleiner als das Maximum sein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El monto anual obligatorio debe ser inferior al máximo.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le montant annuel requis doit être inférieur au maximum.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Verplicht jaarbedrag moet kleiner zijn dan maximum")); }

        // Actions
	};
}



