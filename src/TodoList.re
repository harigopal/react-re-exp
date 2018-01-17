let component = ReasonReact.statelessComponent("TodoList");

let make = (~appState: TodoApp.state, ~appSend, _children) => {
  ...component,
  render: _self =>
    <div>
      (
        ReasonReact.arrayToElement(
          Array.of_list(
            List.map(
              (item: TodoApp.item) =>
                <TodoItem item appSend key=(string_of_int(item.id)) />,
              appState.items
            )
          )
        )
      )
    </div>
};