using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Xml.Linq;

namespace ViewsGenerator
{
    public partial class ClientsEditor : Form
    {
        public ModelDesktop model = null;
        public MainForm mainForm = null;
        public string DataImplFolderPath { get; set; }
        private List<MarketItem> marketClientItemsList = new List<MarketItem>();

        public ClientsEditor()
        {
            InitializeComponent();

            for (int i = 0; i < 199; i++)
            {
                DataGridViewRow row = new DataGridViewRow();
                row.CreateCells(dataGridViewClients);

                row.Cells[0].Value = string.Empty;
                row.Cells[1].Value = string.Empty;
                row.Cells[2].Value = string.Empty;
                row.Cells[3].Value = string.Empty;

                dataGridViewClients.Rows.Add(row);
            }

            SetRowNumber(dataGridViewClients);
        }

        public string GetLanguagePathAndFileName()
        {
            return DataImplFolderPath + "\\clients.xml";
        }

        public void LoadClientsToDataGridView()
        {
            string pathAndFileName = GetLanguagePathAndFileName();

            if (File.Exists(pathAndFileName))
            {
                try
                {
                    XDocument xDoc = XDocument.Load(pathAndFileName);

                    var markets = xDoc.Descendants("Market");

                    int row = 0;

                    foreach (var market in markets)
                    {
                        string marketId = market.Attribute("Market_Id").Value;
                        string marketName = market.Attribute("Market_Name").Value;

                        var clients = market.Descendants("Client");

                        foreach (var client in clients)
                        {
                            string clientId = client.Attribute("Client_Id").Value;
                            string clientName = client.Value;

                            if (dataGridViewClients.Rows.Count > row)
                            {
                                dataGridViewClients.Rows[row].Cells[0].Value = marketId;
                                dataGridViewClients.Rows[row].Cells[1].Value = marketName;
                                dataGridViewClients.Rows[row].Cells[2].Value = clientId;
                                dataGridViewClients.Rows[row].Cells[3].Value = clientName;
                            }

                            row++;
                        }
                    }
                }
                catch (Exception ex)
                {
                    MessageBox.Show("An error occurred while loading clients xml file. Error: " + ex, "Loading Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                }
            }
            else
            {
                MessageBox.Show("Clients xml file doesn't exist in the specified location.", "Loading Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void GetDataFromGrid()
        {
            int n = 0;
            int m = 0;

            foreach (DataGridViewRow row in dataGridViewClients.Rows)
            {
                if (row.Cells["MarketId"].Value != null && int.TryParse(row.Cells["MarketId"].Value.ToString(), out n) &&
                    row.Cells["MarketName"].Value != null &&
                    row.Cells["ClientId"].Value != null && int.TryParse(row.Cells["ClientId"].Value.ToString(), out m) &&
                    row.Cells["ClientName"].Value != null)
                {
                    string marketId = row.Cells["MarketId"].Value.ToString();

                    MarketItem marketItem = marketClientItemsList.Find(x => x.MarketId == marketId);

                    if (marketItem == null)
                    {
                        marketItem = new MarketItem();

                        marketItem.MarketId = row.Cells["MarketId"].Value.ToString();
                        marketItem.MarketName = row.Cells["MarketName"].Value.ToString();

                        ClientItem clientItem = new ClientItem();

                        clientItem.ClientId = row.Cells["ClientId"].Value.ToString();
                        clientItem.ClientName = row.Cells["ClientName"].Value.ToString();

                        if (marketItem.MarketId != "" && marketItem.MarketName != "" && clientItem.ClientId != "" && clientItem.ClientName != "")
                        {
                            marketItem.clientInMarketItemList.Add(clientItem);
                            marketClientItemsList.Add(marketItem);
                        }
                    }
                    else
                    {
                        ClientItem clientItem = new ClientItem();

                        clientItem.ClientId = row.Cells["ClientId"].Value.ToString();
                        clientItem.ClientName = row.Cells["ClientName"].Value.ToString();

                        if (clientItem.ClientId != "" && clientItem.ClientName != "")
                        {
                            marketItem.clientInMarketItemList.Add(clientItem);
                        }
                    }
                }
            }
        }

        private void SaveClients()
        {
            var sortedList = marketClientItemsList.OrderBy(x => Convert.ToInt32(x.MarketId)).ThenBy(x => x.clientInMarketItemList.OrderBy(y => Convert.ToInt32(y.ClientId))).ToList();

            try
            {
                var xElement = new XElement("Root",
                                from market in sortedList
                                select new XElement("Market",
                                         new XAttribute("Market_Id", market.MarketId),
                                         new XAttribute("Market_Name", market.MarketName),
                                         from client in market.clientInMarketItemList
                                         select new XElement("Client", 
                                            new XAttribute("Client_Id", client.ClientId),
                                            client.ClientName
                                       )));

                string pathAndFileName = GetLanguagePathAndFileName();

                xElement.Save(pathAndFileName, SaveOptions.OmitDuplicateNamespaces);
            }
            catch (IOException ex)
            {
                MessageBox.Show("An error occurred while saving clients xml file. Error: " + ex, "Saving File Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void ButtonOK_Click(object sender, EventArgs e)
        {
            GetDataFromGrid();
            SaveClients();

            Close();
        }

        private void SetRowNumber(DataGridView dgv)
        {
            foreach (DataGridViewRow row in dgv.Rows)
            {
                row.HeaderCell.Value = (row.Index + 1).ToString();
            }
        }
    }
}
