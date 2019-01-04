#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_rep_number : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_rep_number() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_rep_number() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_INVALID_REP_NUMBER")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Amount type only applied to entity type \"Escrow\" or \"Assignee\".")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Amount type only applied to entity type \"Escrow\".")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Betragsart wird nur auf Objekttyp \"Escrow\" angewendet.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El tipo de monto sólo se aplica al tipo de entidad \"Custodia\"")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le type de montant ne correspond qu'à l'entité de type Cessionnaire.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Bedragtype is alleen van toepassing op eenheidtype 'Pand'")); }

        // Actions
	};
}



