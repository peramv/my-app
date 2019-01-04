#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_sys_exch_rec_exists : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_sys_exch_rec_exists() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_sys_exch_rec_exists() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_SYS_EXCH_REC_EXISTS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Entity Type and Entity Type Sequence must be populated, OrigTransld must be blank.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Entity Type and Entity Type Sequence must be populated, OrigTransld must be blank.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Objekt-Typ und Objekt-Typ-Abschnitt müssen ausgefüllt sein, Original-Transaktions-ID muss leer sein")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Deben completarse los campos Tipo de entidad y Secuencia de tipo de entidad. Identificación de transacción original debe dejarse en blanco.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le type d'entité et la séquence de type d'entité sont requis, mais le champ du code de transaction d'origine doit être vide.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Eenheidtype en Eeenheidtypevolgorde moeten worden ingevuld, Origineel transactie-ID moet leeg blijven")); }

        // Actions
	};
}



