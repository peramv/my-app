#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_copy_purch_ssn_mismatch : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_copy_purch_ssn_mismatch() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_copy_purch_ssn_mismatch() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_COPY_PURCH_SSN_MISMATCH")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Fund number does not exist, please select existing one or leave it blank and select a fund and class.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Fund number does not exist, please select existing one or leave it blank and select a fund and class.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Fondsnummer existiert nicht, bitte wählen Sie eine existierende Nummer oder lassen Sie dieses Feld frei, und wählen Sie einen Fonds und eine Klasse.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El número de fondo no existe, por favor seleccione uno existente o déjelo en blanco y seleccione un fondo y clase.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le numéro de fonds n'existe pas. Veuillez sélectionner un numéro existant ou laisser ce champ vide et sélectionner un fonds et une classe.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Fondsnummer bestaat niet, selecteer een bestaand nummer of laat het veld leeg en selecteer een fonds en categorie")); }

        // Actions
	};
}



