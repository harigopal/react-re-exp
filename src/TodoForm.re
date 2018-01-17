let str = ReasonReact.stringToElement;

type state = {title: string};

let valueFromInputEvent = event : string => (
                                              event
                                              |> ReactEventRe.Form.target
                                              |> ReactDOMRe.domElementToObj
                                            )##value;

let component = ReasonReact.reducerComponent("TodoForm");

let make = (~appReduce, _children) => {
  ...component,
  initialState: () => {title: ""},
  reducer: (title, _state) => ReasonReact.Update({title: title}),
  render: ({state: {title}, reduce}) =>
    <form
      onSubmit=(
        event => {
          ReactEventRe.Synthetic.preventDefault(event);
          (appReduce(() => TodoApp.AddItem(title)))();
          (reduce(() => ""))();
        }
      )>
      <input
        _type="text"
        id="todo-text-input"
        onChange=(reduce(event => valueFromInputEvent(event)))
        value=title
      />
      <button _type="submit"> (str("Add an item")) </button>
    </form>
};