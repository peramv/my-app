#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_cappedfund_statusw : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_cappedfund_statusw() { }
		~CIFast_IFast_ifastcbo_err_cappedfund_statusw() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_CAPPEDFUND_STATUSW")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Fund %FUND% is capped.  Verify if transaction is allowed.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Warning: %MESSAGE%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Fonds %FUND% ist abgeschlossen. Überprüfen Sie, ob Transaktion zugelassen ist.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El fondo %FUND% tiene un tope. Verifique si se permite la transacción.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le fonds %FUND% est plafonné. Vérifiez si la transaction est autorisée.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Fonds %FUND% is aan grenzen gebonden. Controleer of transactie is toegestaan")); }

        // Actions
	};
}



