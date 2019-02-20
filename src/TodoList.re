type todoItem = string;
type newTodo = string;

type state = {
    todoItems: list(todoItem),
    newTodo: newTodo
};

type action =
    | UpdateNewTodo(newTodo)
    | AddTodo(todoItem)
    | RemoveTodo;

let component = ReasonReact.reducerComponent("TodoList");

let renderTodoItem = (todoItem) => {
    <li key=todoItem>{ReasonReact.string(todoItem)}</li>
};

let renderTodoList = (todos) => {
    <ul>
    {
        todos
        |> List.map(renderTodoItem)
        |> Array.of_list
        |> ReasonReact.array
    }
    </ul>
};

let getLocally = () => {
    let storage = Dom.Storage.localStorage;
    let todos = Dom.Storage.getItem("todos", storage);
    switch(todos) {
        | None => [||] |> Array.to_list;
        | Some(todos) => Js.String.split(",", todos) |> Array.to_list;
    }
};


let saveLocally = (items) => {
    let storage = Dom.Storage.localStorage;
    switch(items) {
        | None => Dom.Storage.setItem("todos", "Nothing", storage)
        | Some(items) => Dom.Storage.setItem("todos", items, storage);
    }
};

let make = (_children) => {
    ...component,
    initialState: () => { todoItems: getLocally(), newTodo: "" },
    reducer: (action, state) => {
        switch (action) {
            | UpdateNewTodo(newTodo) => ReasonReact.Update({ ...state, newTodo: newTodo })
            | AddTodo(todoItem) => ReasonReact.UpdateWithSideEffects(
                { newTodo: "", todoItems: state.todoItems @ [todoItem]}, 
                (self => {
                    self.state.todoItems
                    |> Array.of_list
                    |> Js.Json.stringifyAny
                    |> saveLocally
                }))
            | RemoveTodo => ReasonReact.Update(state)
        }
    },
    render: self => {
        <div>
            <h1>{ReasonReact.string("Todo List")}</h1>
            (renderTodoList(self.state.todoItems))
            <input 
                value={self.state.newTodo}
                onChange=(event => self.send(UpdateNewTodo(ReactEvent.Form.target(event)##value))) />
            <button onClick=(_event => self.send(AddTodo(self.state.newTodo))) >
                {ReasonReact.string("Add To Do")}
            </button>
        </div>
    }
};