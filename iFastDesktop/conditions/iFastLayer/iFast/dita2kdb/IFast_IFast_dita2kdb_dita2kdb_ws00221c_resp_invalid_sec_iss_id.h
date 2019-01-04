#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_sec_iss_id : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_sec_iss_id() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_sec_iss_id() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_INVALID_SEC_ISS_ID")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Allocation information must be set up for systematic record.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Allocation information must be set up for systematic record.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Zuweisungsinformationen müssen für systematischen Planeintrag erstellt werden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Debe configurarse información de asignación para el registro de plan sistemático.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'information sur la répartition doit être saisie avant l’enregistrement des directives.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Allocatiegegevens moeten worden ingesteld voor systeemplanrecord")); }

        // Actions
	};
}



