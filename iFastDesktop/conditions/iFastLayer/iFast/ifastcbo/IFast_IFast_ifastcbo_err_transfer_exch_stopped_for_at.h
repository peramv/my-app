#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_transfer_exch_stopped_for_at : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_transfer_exch_stopped_for_at() { }
		~CIFast_IFast_ifastcbo_err_transfer_exch_stopped_for_at() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_TRANSFER_EXCH_STOPPED_FOR_AT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("This account has transfers/exchanges stopped. Unable to set up allocation.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("This account has transfers/exchanges stopped. Unable to set up allocation.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Für dieses Konto wurden Transfers/Börsenhandel gestoppt. Zuweisung kann nicht erstellt werden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Esta cuenta ha interrumpido transferencias/traspasos. Imposible configurar asignación.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Ce compte a des transferts/échanges arrêtés. Impossible de régler la répartition.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Voor dit account zijn overdrachten/ruiltransacties beëindigd. Allocatie kon niet worden ingesteld")); }

        // Actions
	};
}



