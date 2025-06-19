import { createSlice } from "@reduxjs/toolkit";


const signReducer = createSlice({
    initialState: null,
    name: "sign",
    reducers: {
        signIn(_state, action) {
            return action.payload.name
        },
        signOut(_state, _action) {
            return null;
        }
    }
});

export default signReducer.reducer;