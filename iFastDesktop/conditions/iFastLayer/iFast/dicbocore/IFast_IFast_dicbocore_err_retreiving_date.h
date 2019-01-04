#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dicbocore_err_retreiving_date : public CConditionObject
	{
	public:
		CIFast_IFast_dicbocore_err_retreiving_date() { }
		~CIFast_IFast_dicbocore_err_retreiving_date() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_RETREIVING_DATE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dicbocore")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("This account has transfer in transactions stopped. Unable to set up automatic transfer to this account.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("This account has transfer in transactions stopped. Unable to set up automatic transfer to this account.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Für dieses Konto wurden Transfers in Transaktionen gestoppt. Automatischer Transfer auf dieses Konto kann nicht erstellt werden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Esta cuenta ha interrumpido las transacciones de transferencias de entrada. Imposible configurar transferencia automática a esta cuenta.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Un transfert est arrêté parmi les transactions de ce compte. Impossible de régler le transfert automatique pour ce compte.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Voor dit account is overdracht van transacties beëindigd. Automatische overdracht kon niet worden ingesteld voor dit account")); }

        // Actions
	};
}



