#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_invalid_percent : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_invalid_percent() { }
		~CIFast_IFast_ifastcbo_err_invalid_percent() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_PERCENT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Index Amount must be greater than 0 and less than or equal to 99.99 when Index Type is \"%\".")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Der Index-Betrag muss größer als 0 und größer oder gleich 99,99 sein, wenn die Indexart “%“ ist.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El monto del índice debe ser mayor que  0 e inferior o igual a 99.99 cuando la tasa de índice es \"%\".")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le montant d'indexation doit être supérieur à zéro et inférieur ou égal à 99,99 lorsque le type d'indexation est %.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Indexbedrag moet groter zijn dan 0 en kleiner dan of gelijk aan 99,99 als het indextype '%' is")); }

        // Actions
	};
}



