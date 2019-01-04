#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_no_updates_to_apply : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_no_updates_to_apply() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_no_updates_to_apply() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_NO_UPDATES_TO_APPLY")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Account status may not be assigned to Terminated or Deleted while there is an account balance, unsettled units, or active certificate records exist on the account.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Le statut de compte peut ne pas être defini sur Cloture ou Supprime tant qu'il existe un solde de compte, des unites non reglees ou des enregistrements de certificats dans le compte.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Der Kontostatus darf nicht den Eigenschaften Beendet oder Gelöscht zugewiesen sein, während Kontostand, nicht ausgeglichene Anteile oder aktive Zertifikat-Einträge für das Konto existieren.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El estado de la cuenta no puede definirse como Terminada o Eliminada mientras hay saldo en la cuenta, unidades no liquidadas o mientras existen registros de certificado activos en la cuenta.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le statut du compte ne doit pas être réglé à Fermé ou Supprimé lorsqu'il y a un solde ou des unités non réglées au compte, ou que des enregistrements de certificat actifs existent au compte.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Accountstatus kan niet worden toegewezen aan Beëindigd of Gewist als er een accountsaldo, onbetaalde eenheden, of actieve certificaatrecords bestaan voor het account")); }

        // Actions
	};
}



