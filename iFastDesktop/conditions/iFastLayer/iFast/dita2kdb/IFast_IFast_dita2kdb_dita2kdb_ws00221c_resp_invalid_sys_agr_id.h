﻿#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_sys_agr_id : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_sys_agr_id() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_sys_agr_id() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_INVALID_SYS_AGR_ID")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Apartment number missing or not found in database and apartment-level match required.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Apartment number missing or not found in database and apartment-level match required.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Apartment-Nummer fehlt oder wurde in der Datenbank nicht gefunden; Entsprechung auf Apartment-Level ist erforderlich.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Falta el número de apartamento o no se encontró en la base de datos y se requiere la comparación a nivel de apartamentos")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le numéro d'appartement est manquant ou introuvable dans la base de données et une correspondance au niveau de l'appartement est requise.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Appartementsnummer ontbreekt of kon niet worden gevonden in de database en een overeenkomst op appartementsniveau is vereist")); }

        // Actions
	};
}



