#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_accts_not_related : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_accts_not_related() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_accts_not_related() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_ACCTS_NOT_RELATED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Entity Type, Entity Type Sequence and OrigTransld must be populated.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Entity Type, Entity Type Sequence and OrigTransld must be populated.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Objekt-Typ, Objekt-Typ-Abschnitt und Original-Transaktions-ID müssen ausgefüllt sein")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Deben completarse los campos Tipo de entidad, Secuencia de tipo de entidad e Identificación de transacción original")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le type d'entité, la séquence de type d'entité et le code de transaction d'origine sont requis.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Eenheidtype, Eenheidtypevolgorde en Origineel transctie-ID moeten worden ingevuld")); }

        // Actions
	};
}



