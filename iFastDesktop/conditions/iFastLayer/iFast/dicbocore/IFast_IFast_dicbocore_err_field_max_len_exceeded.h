#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dicbocore_err_field_max_len_exceeded : public CConditionObject
	{
	public:
		CIFast_IFast_dicbocore_err_field_max_len_exceeded() { }
		~CIFast_IFast_dicbocore_err_field_max_len_exceeded() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FIELD_MAX_LEN_EXCEEDED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dicbocore")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("This account has transfers/exchanges stopped. Unable to set up automatic transfer.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Les virements et echanges de ce compte ont ete arretes. Impossible de definir un virement automatique.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Für dieses Konto wurden Transfers/Börsenhandel gestoppt. Automatischer Transfer kann nicht erstellt werden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Esta cuenta ha interrumpido transferencias/traspasos. Imposible configurar transferencia automática.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Des transferts/échanges sont arrêtés pour ce compte. Impossible de régler le transfert automatique.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Voor dit account zijn overdrachten/ruiltransacties beëindigd. Automatische overdracht kon niet worden ingesteld")); }

        // Actions
	};
}



