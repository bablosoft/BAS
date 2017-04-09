<div class="container-fluid">
  <div class="col-xs-12">
        <form class="form-horizontal">
          <div class="form-group">
            <div class="col-xs-2">
              <div class="input-group">
                <span data-preserve="true" data-preserve-type="select" data-preserve-id="Table">
                  <select class="form-control input-sm" id="Table" placeholder="Result">
                      <% _Schema.forEach(function(t){ %>
                       <option value="<%= t.id %>"><%= t.description %></option>
                      <% }) %>
                  </select>
                </span>
              </div>
            </div>
            <label class="control-label text-right tr" style="padding-top:5px !important;">Table</label>
          </div>
        </form>
      </div>
    <%= _.template($('#input_constructor').html())({id:"RecordId", description:tr("Record id. Leave blank to update last record obtained as resource"), default_selector: "string", disable_int:true}) %>

    <div class="container-fluid">
      <div class="tooltipinternal tr">Set only those fields that you want to change in the database.</div>
    </div>

    <% _Schema.forEach(function(t){ %>
        <% t["columns"].forEach(function(c){ %>
          <span data-table-id="<%= t["id"] %>" style="<%= (t["id"] != _Schema[0]["id"])?"display:none":"" %>" data-id="<%= c["id"] %>">
            <% if(c["type"] == "string"){ %>
              <%= _.template($('#input_constructor').html())({id:"Table_" + t["id"] + "_Column_" + c["id"], description:c["description"], default_selector: "string", disable_int:true}) %>          
            <% } %>
            <% if(c["type"] == "int"){ %>
              <%= _.template($('#input_constructor').html())({id:"Table_" + t["id"] + "_Column_" + c["id"], description:c["description"], default_selector: "expression",value_string: "", disable_string:true, min_number: -999999}) %>          
            <% } %>
            <% if(c["type"] == "bool"){ %>
              <%= _.template($('#input_constructor').html())({id:"Table_" + t["id"] + "_Column_" + c["id"], description:c["description"], size:4, default_selector: "string", disable_int:true, variants: ["true","false"]}) %>          
            <% } %>
            <% if(c["type"] == "date"){ %>
              <%= _.template($('#input_constructor').html())({id:"Table_" + t["id"] + "_Column_" + c["id"], description:c["description"], default_selector: "expression", disable_string:true}) %>          
            <% } %>
          </span>
        <% }) %>      
    <% }) %>


    
</div>
<%= _.template($('#back').html())({action:"executeandadd", visible:true}) %>
