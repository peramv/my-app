#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dicbocore_err_workorder_cbe_already_registered : public CConditionObject
	{
	public:
		CIFast_IFast_dicbocore_err_workorder_cbe_already_registered() { }
		~CIFast_IFast_dicbocore_err_workorder_cbe_already_registered() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_WORKORDER_CBE_ALREADY_REGISTERED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dicbocore")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Full transfer is not allowed on allocated transfers. Please enter an amount greater than zero.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Full transfer is not allowed on allocated transfers.  Please enter an amount greater than zero.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Voller Transfer ist nicht erlaubt bei zugewiesenen Transfers. Bitte geben Sie einen Betrag ein, der größer als Null ist.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se permiten transferencias totales sobre las transferencias asignadas  Por favor introduzca un monto mayor que cero.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Un transfert total n'est pas autorisé pour les transferts répartis. Veuillez saisir un montant supérieur à zéro.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Volledige overdracht is niet toegestaan bij gealloceerde overdracht. Voer een bedrag in dat groter is dan nul")); }

        // Actions
	};
}



