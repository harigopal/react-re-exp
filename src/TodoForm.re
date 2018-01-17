let str = ReasonReact.stringToElement;

type state = {title: string};

let valueFromInputEvent = event : string => (
                                              event
                                              |> ReactEventRe.Form.target
                                              |> ReactDOMRe.domElementToObj
                                            )##value;

let component = ReasonReact.reducerComponent("TodoForm");

let make = (~appSend, _children) => {
  ...component,
  initialState: () => {title: ""},
  reducer: (title, _state) => ReasonReact.Update({title: title}),
  render: ({state: {title}, send}) =>
    <form
      onSubmit=(
        event => {
          ReactEventRe.Synthetic.preventDefault(event);
          appSend(TodoApp.AddItem(title));
          send("");
        }
      )>
      <input
        _type="text"
        id="todo-text-input"
        onChange=(event => send(valueFromInputEvent(event)))
        value=title
      />
      <button _type="submit"> (str("Add an item")) </button>
    </form>
};