using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace ViewsGenerator
{
    public partial class AddSubstitutionSetForm : Form
    {
        public ModelDesktop model = null;
        private SubstitutionSetItem newSubstitutionSetItem = new SubstitutionSetItem();

        public SubstitutionSetItem NewSubstitutionSetItem 
        { 
            get { return newSubstitutionSetItem; }
            set { newSubstitutionSetItem = value; } 
        }        

        public AddSubstitutionSetForm()
        {
            InitializeComponent();

            this.buttonOK.Enabled = false;
        }

        public void InitializeData()
        {
            foreach (var lang in model.uniqueIdToCountryLanguageDictionary)
            {
                comboBoxLanguage.Items.Add(lang.Value);
            }

            foreach (var market in model.marketClientItemList.Select(x => x.MarketName).Distinct())
            {
                comboBoxMarket.Items.Add(market);
            }

            comboBoxMarket.SelectedIndex = 0;
        }

        private void buttonOK_Click(object sender, EventArgs e)
        {
            if (this.textBoxNewSubstitutionSetName.Text.Trim() != "" &&
                this.comboBoxLanguage.Text.Trim() != "")
            {
                string substitutionSetName = this.textBoxNewSubstitutionSetName.Text.Trim();
                string language = this.comboBoxLanguage.Text.Trim();
                string market = this.comboBoxMarket.Text.Trim();
                string client = this.comboBoxClient.Text.Trim();

                if (IsNewSubstitutionSetAlreadyInUse(substitutionSetName, language, market, client))
                {
                    MessageBox.Show("Substitution set is already in use, change properties to make substitution set unique.", "New Field Name Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                }
                else
                {
                    CreateNewSubstitutionSet(substitutionSetName, language, market, client);
                    this.DialogResult = DialogResult.OK;

                    this.Close();
                }
            }
        }

        private bool IsNewSubstitutionSetNameAlreadyInUse(string substitutionSetName, out SubstitutionSetItem substitutionSetWithSameName)
        {
            bool isInUse = false;
            substitutionSetWithSameName = null;

            var duplicate = model.substitutionsList.Where(x => x.isNewSubstitutionSet == false && x.Name == substitutionSetName);

            if (duplicate.Count() > 0)
            {
                isInUse = true;
                substitutionSetWithSameName = duplicate.ElementAt(0);
            }

            return isInUse;
        }

        private bool IsNewSubstitutionSetAlreadyInUse(string substitutionSetName, string language, string market, string client)
        {
            bool isInUse = false;

            if (market == "No Market")
            {
                market = "";
            }

            if (client == "No Client")
            {
                client = "";
            }

            var duplicate = model.substitutionsList.Where(x => x.isNewSubstitutionSet == false && x.Name == substitutionSetName && 
                                    string.Equals(x.Language, language, StringComparison.CurrentCultureIgnoreCase) && x.MarketName == market && x.ClientName == client);

            if (duplicate.Count() > 0)
            {
                isInUse = true;
            }

            return isInUse;
        }

        private void ComboBoxLanguage_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (this.textBoxNewSubstitutionSetName.Text.Trim() != "" &&
                this.comboBoxLanguage.Text.Trim() != "")
            {
                this.buttonOK.Enabled = true;
            }
            else
            {
                this.buttonOK.Enabled = false;
            }
        }

        private void TextBoxSubstitutionSetName_Leave(object sender, EventArgs e)
        {
            if (this.textBoxNewSubstitutionSetName.Text.Trim() != "" &&
                this.comboBoxLanguage.Text.Trim() != "")
            {
                this.buttonOK.Enabled = true;
            }
            else
            {
                this.buttonOK.Enabled = false;
            }
        }

        private void CreateNewSubstitutionSet(string substitutionSetName, string language, string market, string client)
        {
            newSubstitutionSetItem.isNewSubstitutionSet = true;
            newSubstitutionSetItem.Name = substitutionSetName;
            
            string newSubstitutionSetCreationIndex = "";

            SubstitutionSetItem substitutionSetWithSameName = null;
            // The first case is for substitution set that have the same name as one of existing substitution sets, but everything else is different
            if (IsNewSubstitutionSetNameAlreadyInUse(substitutionSetName, out substitutionSetWithSameName))
            {
                newSubstitutionSetCreationIndex = substitutionSetWithSameName.SubstitutionSetCreationIndex;
            }
            // Totaly new substitution set
            else
            {
                newSubstitutionSetCreationIndex = (Convert.ToInt32(model.substitutionsList.Max(x => x.SubstitutionSetCreationIndexInt)) + 1).ToString();
            }

            string languageId = "000";
            if (languageId != "")
            {
                newSubstitutionSetItem.Language = language;
                int nLanguageId = Convert.ToInt32(model.uniqueIdToCountryLanguageDictionary.First(x => x.Value == language).Key);

                if (nLanguageId < 10)
                {
                    languageId = "00" + nLanguageId.ToString();
                }
                else if (nLanguageId < 100)
                {
                    languageId = "0" + nLanguageId.ToString();
                }
                else
                {
                    languageId = nLanguageId.ToString();
                }
            }
            

            string marketId = "000";
            if (market != "" && market != "No Market")
            {
                newSubstitutionSetItem.MarketName = market;
                int nMarketId = Convert.ToInt32(model.marketClientItemList.First(x => x.MarketName == market).MarketId);
                newSubstitutionSetItem.MarketId = nMarketId.ToString();

                if (nMarketId < 10)
                {
                    marketId = "00" + nMarketId.ToString();
                }
                else if (nMarketId < 100)
                {
                    marketId = "0" + nMarketId.ToString();
                }
                else
                {
                    marketId = nMarketId.ToString();
                }
            }

            string clientId = "000";
            if (client != "" && client != "No Client")
            {
                newSubstitutionSetItem.ClientName = client;
                int nClientId = Convert.ToInt32(model.marketClientItemList.First(x => x.MarketName == market).clientInMarketItemList.First(y => y.ClientName == client).ClientId);
                newSubstitutionSetItem.ClientId = nClientId.ToString();

                if (nClientId < 10)
                {
                    clientId = "00" + nClientId.ToString();
                }
                else if (nClientId < 100)
                {
                    clientId = "0" + nClientId.ToString();
                }
                else
                {
                    clientId = nClientId.ToString();
                }
            }

            string newSubstitutionSetId = "002_" + newSubstitutionSetCreationIndex + "_" + languageId + "_" + marketId + "_" + clientId;

            newSubstitutionSetItem.SubstitutionSetCreationIndexInt = Convert.ToInt32(newSubstitutionSetCreationIndex.TrimStart('0'));
            newSubstitutionSetItem.SubstitutionSetId = newSubstitutionSetId;
            newSubstitutionSetItem.SubstitutionSetShortId = "002_" + newSubstitutionSetCreationIndex;
            newSubstitutionSetItem.KeysName = "aKeys_" + newSubstitutionSetId;
            newSubstitutionSetItem.ValuesName = "aValues_" + newSubstitutionSetId;
            newSubstitutionSetItem.SubstitutionSetChooserFunction = "chooser_ss_002_" + newSubstitutionSetCreationIndex;

            model.substitutionsList.Add(newSubstitutionSetItem);
        }

        private void ComboBoxMarket_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (comboBoxMarket.SelectedItem != null)
            {
                string market = comboBoxMarket.SelectedItem.ToString();

                MarketItem marketItem = model.marketClientItemList.Find(x => x.MarketName == market);

                if (marketItem != null)
                {
                    comboBoxClient.Items.Clear();

                    foreach (var client in marketItem.clientInMarketItemList)
                    {
                        comboBoxClient.Items.Add(client.ClientName);
                    }

                    comboBoxClient.SelectedIndex = 0;
                }
            }
        }
    }
}
